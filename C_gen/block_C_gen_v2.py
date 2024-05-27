import torch
from torch import nn

class Net(nn.Module): # define MLP model
    def __init__(self, input_size, hidden_size, output_size):
        super(Net, self).__init__()
        self.fc1 = nn.Linear(input_size, hidden_size)
        self.relu = nn.ReLU()
        self.tanh = nn.Tanh()
        self.fc2 = nn.Linear(hidden_size, output_size)

    def forward(self, x):
        x = self.fc1(x)
        # x = self.relu(x)
        x = self.tanh(x)
        x = self.fc2(x)
        return x

activ_func = 'tanh'

Lay = [6,4,1] # input_size, hidden_size, output_size

loc_model = '../'
name_model = 'model.pth'
loc_gen = './'
name_gen = 'AutoMLP_gen.cpp'


m_state_dict = torch.load(loc_model+name_model)
# cpp_front= open(loc_model+"AutoMLP_00_head.cpp")     ## 把这个头文件放在模型目录，如果放其它目录，修改这里的位置
cpp_front= open("./AutoMLP_00_head.cpp")     ## where script is!
with open(loc_gen+name_gen,"w") as cpp:
        pass #cpp.write(line)
for line in cpp_front.readlines(): 
    with open(loc_gen+name_gen,"a") as cpp:
        cpp.write(line)
#             print(2)
cpp_front.close()

# bit-widths
with open(loc_gen+name_gen,"a") as cpp:
    cpp.write("typedef float ap_f;\n\n")
#     cpp.write("typedef ap_fixed<8,4> ap_f;\n\n") 

# interface   01
# cpp_interface = open(loc_model+"AutoMLP_01_interface.cpp")    ## 把这个头文件放在模型目录，如果放其它目录，修改这里的位置
cpp_interface = open("./AutoMLP_01_interface.cpp")    ## where script is!
for line in cpp_interface.readlines():  
    with open(loc_gen+name_gen,"a") as cpp:
        cpp.write(line)      
cpp_interface.close() 

# 数组定义
fp = open(loc_gen+name_gen,'a')       
for i in range(1,len(Lay)):
#         print("ap_f "+chr(ord('A')+i)+'['+str(Lay[i])+'];')
    fp.write("ap_f "+chr(ord('A')+i)+'['+str(Lay[i])+'];\n')
fp.close()


#     MLP wights parameters 
fp = open(loc_gen+name_gen,'a')

flag = True
k=1
#     for name,param in new_m.named_parameters():    #new_m 不应该跟着net走
for name,param in m_state_dict.named_parameters():
#         print(param)
    temp =  param
    temp = temp.float()
#         print(temp)
    temp1 = temp.numpy
    temp2= temp.tolist()
    if flag == True:
        flag = False
        fp.write('ap_f Hw'+str(k)+'['+str(len(temp2))+']['+str(len(temp2[0]))+'] = {')
        for i in range(len(temp2)-1):
            fp.write('{')
            for j in range(len(temp2[0])-1):
                fp.write(str(temp2[i][j])+',')
            fp.write(str(temp2[i][len(temp2[0])-1])+'},\n')
        #尾巴
        fp.write('{')
        for j in range(len(temp2[0])-1):
            fp.write(str(temp2[len(temp2)-1][j])+',')
        fp.write(str(temp2[len(temp2)-1][len(temp2[0])-1])+'}')
        fp.write('};\n\n\n')
    else:
        flag = True
        fp.write('ap_f Hb'+str(k)+'['+str(len(temp2))+'] = {')
        k +=1
        for i in range(len(temp2)-1):
            fp.write(str(temp2[i])+',')
        fp.write(str(temp2[len(temp2)-1]))
        fp.write('};\n\n\n')

fp.close()    

#     MLP intercace, diagonis
fp = open(loc_gen+name_gen,'a')
for i in range(len(Lay)-2):
    print('    for (int i = 0; i < '+str(Lay[i+1])+'; i++) {')
    print('        '+chr(ord('A')+i+1)+'[i] = 0;')
    print('        for (int j = 0; j < '+str(Lay[i])+'; j++) {')
    print('            '+chr(ord('A')+i+1)+'[i] = '+chr(ord('A')+i+1)+'[i] + '+chr(ord('A')+i)+'[j] * Hw'+str(i+1)+'[i][j];')
    print('        }')
    print('        '+chr(ord('A')+i+1)+'[i] = '+chr(ord('A')+i+1)+'[i] + Hb'+str(i+1)+'[i] ;')
    print('        if('+chr(ord('A')+i+1)+'[i] < 0){'+chr(ord('A')+i+1)+'[i] = 0;}')
    print('    }')

    fp.write('    for (int i = 0; i < '+str(Lay[i+1])+'; i++) {\n')
    fp.write('        '+chr(ord('A')+i+1)+'[i] = 0;\n')
    fp.write('        for (int j = 0; j < '+str(Lay[i])+'; j++) {\n')
    fp.write('            '+chr(ord('A')+i+1)+'[i] = '+chr(ord('A')+i+1)+'[i] + '+chr(ord('A')+i)+'[j] * Hw'+str(i+1)+'[i][j];\n')
    fp.write('        }\n')
    fp.write('        '+chr(ord('A')+i+1)+'[i] = '+chr(ord('A')+i+1)+'[i] + Hb'+str(i+1)+'[i] ;\n')
    if activ_func == 'tanh':  ## no need 'test'
        fp.write('        '+chr(ord('A')+i+1)+'[i] = 2/(1+expf(-2*'+chr(ord('A')+i+1)+'[i]))-1;')
    elif activ_func == 'sigmoid':# no need 'test
        fp.write('        '+chr(ord('A')+i+1)+'[i] = 1/(1+expf(-1*'+chr(ord('A')+i+1)+'[i]));')
    else:
        fp.write('        if('+chr(ord('A')+i+1)+'[i] < 0){'+chr(ord('A')+i+1)+'[i] = 0;}\n')
    fp.write('    }\n')   
fp.close()    

fp = open(loc_gen+name_gen,'a')
for i in range(len(Lay)-2,len(Lay)-1):
    print('    for (int i = 0; i < '+str(Lay[i+1])+'; i++) {')
    print('        '+chr(ord('A')+i+1)+'[i] = 0;')
    print('        for (int j = 0; j < '+str(Lay[i])+'; j++) {')
    print('            '+chr(ord('A')+i+1)+'[i] = '+chr(ord('A')+i+1)+'[i] + '+chr(ord('A')+i)+'[j] * Hw'+str(i+1)+'[i][j];')
    print('        }')
    print('        '+chr(ord('A')+i+1)+'[i] = '+chr(ord('A')+i+1)+'[i] + Hb'+str(i+1)+'[i] ;')
    print('    }')
    #开始写入result
    print('    if ('+chr(ord('A')+i+1)+'[0] > '+chr(ord('A')+i+1)+'[1])')
    print('        {result = 0 ;}')
    print('    else')
    print('        {result = 1 ;}')
    print('}')

    fp.write('    for (int i = 0; i < '+str(Lay[i+1])+'; i++) {\n')
    fp.write('        '+chr(ord('A')+i+1)+'[i] = 0;\n')
    fp.write('        for (int j = 0; j < '+str(Lay[i])+'; j++) {\n')
    fp.write('            '+chr(ord('A')+i+1)+'[i] = '+chr(ord('A')+i+1)+'[i] + '+chr(ord('A')+i)+'[j] * Hw'+str(i+1)+'[i][j];\n')
    fp.write('        }\n')
    fp.write('        '+chr(ord('A')+i+1)+'[i] = '+chr(ord('A')+i+1)+'[i] + Hb'+str(i+1)+'[i] ;\n')
    fp.write('    }\n')
    #开始写入result
    fp.write('    if ('+chr(ord('A')+i+1)+'[0] > '+chr(ord('A')+i+1)+'[1])    // the logic here is for binary classification, need adjust\n')
    fp.write('        {result = 0 ;}\n')
    fp.write('    else\n')
    fp.write('        {result = 1 ;}\n')
    fp.write('    out[0] = result;\n')
    fp.write('}\n')
fp.close() 