#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<list>

using namespace std;

int main(){
    string fileforinput;
    string fileforoutput1 = "filesforinput/dirs_200.txt";
    string fileforoutput2 = "filesforinput/dirs_403.txt";
    string fileforoutput3 = "filesforinput/files.txt";
    
    fstream fp1,fp2,fp3,fp4;

    cin >> fileforinput;

    fp1.open(fileforinput.c_str(), ios::in);
    fp2.open(fileforoutput1.c_str(), ios::out | ios::trunc);
    fp3.open(fileforoutput2.c_str(), ios::out | ios::trunc);
    fp4.open(fileforoutput3.c_str(), ios::out | ios::trunc);


    string content;
    int newlinecount = 0;
    bool starttorecord_dir_200 = false;
    bool starttorecord_dir_403 = false;
    bool starttorecord_file = false;
    bool starttorecord = starttorecord_dir_200 | starttorecord_dir_403 | starttorecord_file;

    list<string>  finddir_200;
    list<string>  finddir_403;
    list<string>  findfile;
    if(fp1 && fp2){
        while(getline(fp1, content)){
            if(content.find("Dirs found with a 200 response:")!=string::npos){
                starttorecord_dir_200 = true;
                starttorecord_dir_403 = false;
                starttorecord_file = false;
                starttorecord = starttorecord_dir_200 | starttorecord_dir_403 | starttorecord_file;
                continue;
            }
            else    if(content.find("Dirs found with a 403 response:")!=string::npos){
                starttorecord_dir_200 = false;
                starttorecord_dir_403 = true;
                starttorecord_file = false;
                starttorecord = starttorecord_dir_200 | starttorecord_dir_403 | starttorecord_file;
                continue;
            }
            else    if(content.find("Files found with a 200 responce:")!=string::npos){
                starttorecord_dir_200 = false;
                starttorecord_dir_403 = false;
                starttorecord_file = true;
                starttorecord = starttorecord_dir_200 | starttorecord_dir_403 | starttorecord_file;
                continue;
            }
            else    if(content.find("/")!=string::npos || content.empty()){
            }
            else {
                //cout<<"here:"<<content<<endl;
                starttorecord_dir_200 = false;
                starttorecord_dir_403 = false;
                starttorecord_file = false;
                starttorecord = starttorecord_dir_200 | starttorecord_dir_403 | starttorecord_file;
            }

            if(starttorecord){
                    if(starttorecord_dir_200 && !content.empty() && content!="/")
                        finddir_200.push_back(content);
                    else if(starttorecord_dir_403 && !content.empty() && content!="/")
                        finddir_403.push_back(content);
                    else if(starttorecord_file && !content.empty()){
                        if(content.find(".html")!=string::npos || content.find(".htm")!=string::npos || content.find(".php")!=string::npos || content.find(".js")!=string::npos)
                            findfile.push_back(content);
                    }
            }
        }
    }

    //cout<<"find_dir_200\n";
    for(list<string>::iterator it=finddir_200.begin(); it!=finddir_200.end(); ++it){
        fp2<<*it<<endl;
    }

    //cout<<"find_dir_403\n";
    for(list<string>::iterator it=finddir_403.begin(); it!=finddir_403.end(); ++it){
        fp3<<*it<<endl;
    }

    //cout<<"find_file\n";
    for(list<string>::iterator it=findfile.begin(); it!=findfile.end(); ++it){
       fp4<<*it<<endl;
    }

    fp1.close();
    fp2.close();
    fp3.close();
    fp4.close();
}
