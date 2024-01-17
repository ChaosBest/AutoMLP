# with open('ClassNet.py',"a") as cpp:
#         cpp.write("typedef ap_fixed<"+str(i+10)+","+str(i)+"> ap_f;\n\n")
        
        

def lay_gen(x):
    with open('ClassNet.py',"w") as f_Net:
        pass 
    with open('ClassNet.py',"a") as f_Net:
        f_Net.write('import torch\n')
        f_Net.write('import torch.nn.functional as Fun\n')
        f_Net.write('class Net(torch.nn.Module):\n')
        f_Net.write('    def __init__(self, n_feature'+''.join([', n_hidden'+(str(i) if i > 0 else '') for i in range(x)])+', n_output):\n')
        f_Net.write('        super(Net, self).__init__()\n')
        f_Net.write('        self.hidden = torch.nn.Linear(n_feature, n_hidden)\n')
        for i in range(1,x):
            f_Net.write('        self.hidden'+str(i)+' = torch.nn.Linear(n_hidden'+(str(i-1) if i > 1 else '') +', n_hidden'+str(i)+')\n')
        f_Net.write('        self.out = torch.nn.Linear(n_hidden'+(str(x-1) if x > 1 else '')+', n_output)\n')
        f_Net.write('\n    def forward(self,x):\n')
        for i in range(x):
            if activ_func == 'sigmoid':f_Net.write('        x = Fun.sigmoid(self.hidden'+(str(i) if i > 0 else '')+'(x))\n')
            elif activ_func == 'tanh':f_Net.write('        x = Fun.tanh(self.hidden'+(str(i) if i > 0 else '')+'(x))\n')
            else:f_Net.write('        x = Fun.relu(self.hidden'+(str(i) if i > 0 else '')+'(x))\n')
        f_Net.write('        x = self.out(x)\n        return x\n')    
def model(Lay):
    with open('net.py',"w") as f_Net:
        pass 
    with open('net.py',"w") as f_Net:
        last = len(Lay) - 2
        f_Net.write('net = Net(n_feature=Lay[0]'+''.join([', n_hidden'+(str(i) if i > 0 else '')+'=Lay['+str(i+1)+']' for i in range(last)])+',n_output=Lay['+str(last+1)+'])')
#     net = Net(n_feature=Lay[0], n_hidden=Lay[1],n_output=Lay[2])


# Lay = [7,16,16,16,2]
# Lay = [7,2,2,2]

lay_gen(len(Lay)-2)

model(Lay)