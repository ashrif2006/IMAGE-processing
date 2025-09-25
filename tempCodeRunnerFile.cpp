#include <iostream>
using namespace std;
#include <string>
#include "Image_Class.h"


#include<cstdlib>

Image filter_reverse_color(string name);
Image filter_gray(string name);
Image filter_balck_and_white(string name);
void menu();
void editing();

void to_show_new_image(Image img){
    string name;
    int op;
    cout<<"";
    cout << "\n Enter a name to save the edited image (without extension): ";
    cin>>name;
    cout << "\nChoose a file format to save the image:\n";
    cout << "\t1 - .jpeg\n";
    cout << "\t2 - .jpg\n";
    cout << "\t3 - .png\n";
    cout << "\t4 - .bmp\n";
    cout << "Enter your choice (1-4): ";
    cin>>op;
    string newImage;
    switch (op)
    {
    case 1:
        newImage=name+".jpeg";
        break;
    case 2:
        newImage=name+".jpg";
        break;
    case 3:
        newImage=name+".png";
        break;
    case 4:
        newImage=name+".bmp";
        break;
    
    default:
        cout << "Invalid choice. Defaulting to .jpg\n";
    }

    char o;
    cout << "\n Do you want to save the edited image? (Y/N): ";
    cin>>o;
    if(o=='Y'||o=='y'){

        bool saved=img.saveImage(newImage);
        if(saved){
            string com="start "+newImage;
        system(com.c_str());
        }else{
            cout<<"Failed to save image.\n";
        }

    }else cout << "Image not saved.\n";
    
    
    
    

    

}



void editing(){
    string image_name;
    cout << "\n Enter the full path of the image file:";
    getline(cin , image_name);
    
    int op;
    cout << "\n Available Filters:\n";
    cout << "\t1 - Grayscale\n";
    cout << "\t2 - Black & White\n";
    cout << "\t3 - Reverse Colors\n";
    cout << "Please choose a filter (1, 2, 3, 4, 5, ...): ";
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
    case 4:
        to_show_new_image(merge(image_name));
        break; 
    default:
            cout << " Invalid option.\n";   
    

    }
    
    }


void menu(){
    string x;
    do
    {
        int op;
        cout << "Welcome to the Photo Editing Program!\n";
        cout << "\t1 - Edit an image\n";
        cout << "\t2 - Exit the program\n";
        cout << "Please choose an option (1 or 2): ";
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
                cout << " Invalid option.\n";
        }
        cout << "\n Would you like to edit another image? (Y/N): ";
        
        cin>>x;
    } while (x=="Y" || x=="y" || x=="yes");
    

    


}

Image merge(string name1){
    Image img1;
    Image img2;
    string name2;
    cout<<"enter the name for image 2:";
    cin>>name2;
    try{
        img1.loadNewImage(name1);
        img2.loadNewImage(name2);
    }catch(...){
        cout<<"file not found"<<endl;
    }
    for(int w=0;w<img1.width;w++){
        for(int h=0;h<img1.height;h++){
            for(int i=0;i<3;i++){
                img1(w,h,i)+=img1(w,h,i);
            }
        }
    }
    return img1;
    
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
