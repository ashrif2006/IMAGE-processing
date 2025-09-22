#include <iostream>
using namespace std;
#include "Image_Class.h"

#include<cstdlib>

Image filter_reverse_color(string name);
Image filter_gray(string name);
Image filter_balck_and_white(string name);
void menu();
void editing();

void to_show_new_image(Image img){
    string name;
    cout<<"enter the name to save image\n";
    cin>>name;
    string newImage=name+".png";
    bool saved=img.saveImage(newImage);
    if(saved){
        string com="start "+newImage;
    system(com.c_str());
    }else{
        cout<<"Failed to save image.\n";
    }

    

}



void editing(){
    string image_name;
    cout<<"\t\tenter the path for image\n";
    cin>>image_name;
    int op;
    cout<<"\t\tthe filters is:\n";
    cout<<"\t\t\t1-gray\n";
    cout<<"\t\t\t2-black and white\n";
    cout<<"\t\t\t3-reverse color\n";
    cout<<"\t\t\tchoes your option\n";
    cin>>op;
    switch (op){
    case 1:
        to_show_new_image(filter_gray(image_name));
        break;
    case 2:
        to_show_new_image(filter_balck_and_white(image_name));
        break; 
    case 3:
        to_show_new_image(filter_reverse_color(image_name));
        break; 
    default:
            cout << "❌ Invalid option.\n";   
    

    }
    
    }


void menu(){
    string x;
    do
    {
        int op;
    cout<<"Hi there! Welcome to our photo editing program\n";
    cout<<"\t1-to editing \n";
    cout<<"\t2-to exict\n";
    cout<<"choase the option\n";
    cin>>op;
    switch (op)
    {
    case 1:
        editing();    
        break;
    case 2:
        exit(0);
        break;
    default:
        cout << "❌ Invalid option.\n";
    }
    cout<<"Do you want to create more images:?{Y or N} \n";
    
    cin>>x;
    } while (x=="Y" || x=="y" || x=="yes");
    

    


}

Image filter_gray(string name){

    Image img;
    try{
        img.loadNewImage(name);
    }catch(...){
        cout<<"file not found"<<endl;
        return img;
    }

    

    for (int w= 0; w < img.width; w++) {
        for (int h=0;h<img.height;h++) {
            unsigned int avg=0;
            for (int i=0;i<3;i++) {
                avg+=img(w,h,i);
            }
            avg/=3;
            
            for (int i=0;i<3;i++) {
                img(w,h,i)=avg;
            }
        }
    }
    return img;
}

Image filter_balck_and_white(string name){
    Image img;
    try{
        img.loadNewImage(name);
    }catch(...){
        cout<<"file not found"<<endl;
        return img;
    }

    for(int w=0;w<img.width;w++){
        for(int h=0;h<img.height;h++ ){
            unsigned int avg=0;
            for(int i=0;i<3;i++){
                avg+=img(w,h,i);
            }
            avg/=3;
            for(int i=0;i<3;i++){
                if(avg>128){
                    img(w,h,i)=255;
                }else{
                    img(w,h,i)=0;
                }
            }
        }
    }
    return img;
}

Image filter_reverse_color(string name){
    Image img;
    try{
        img.loadNewImage(name);
    }catch(...){
        cout<<"file not found\n";
    }
    for(int w=0;w<img.width;w++){
        for(int h=0;h<img.height;h++){
            
            for(int i=0;i<3;i++){
                img(w,h,i)=255-img(w,h,i);
            }
            

        }
    }
    return img;
}


int main() {

    
    menu();


    return 0;
}
