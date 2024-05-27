#include "AutoMLP_gen.hpp"
#include "data.hpp"

int main() {
    
    int correct_count = 0;
    int total_count = 0;
    
    for(int i = 0; i < data_len; i++){
        float input_data[6] = {data[i][1], data[i][2], data[i][3], data[i][4], data[i][5], data[i][6]};
        int len = sizeof(input_data) / sizeof(input_data[0]);
        
        // Output data
        float output_data[1] = {2}; // Initializing the output array
        
        // Call the AF_classifier function
        AF_classifier(input_data, output_data, len);
        
        // Check if the classification result is correct
        if(output_data[0] == data[i][0]){
            correct_count++;
        }
        
        total_count++;
    }
    
    // Calculate the accuracy
    float accuracy = (float)correct_count / total_count * 100;
    std::cout << "Accuracy: " << accuracy << "%" << std::endl;



    // // Input data
    // float input_data[6] = {-167,765,845,815,10535,810.385};
    // int len = sizeof(input_data) / sizeof(input_data[0]);
    
    // // Output data
    // float output_data[1] = {2}; // Initializing the output array
    
    // // Call the AF_classifier function
    // AF_classifier(input_data, output_data, len);
    
    // // Print the result
    // std::cout << "Classification Result: " << output_data[0] << std::endl;
    
    return 0;
}