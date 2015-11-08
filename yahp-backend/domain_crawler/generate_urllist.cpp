#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int main(){
    char fileforinput[]="filesforinput/in.txt";
    char fileforoutput[]="urllist.txt";
    fstream fp1,fp2,fp3;
    fp1.open(fileforinput, ios::in);
    fp2.open(fileforoutput, ios::out | ios::app);

    string domain;
    cin>>domain;
    
    //cout<<domain<<endl;

    string doubledash="//";
    size_t found;
    
    if(fp1 && fp2 && domain!=""){
        string garbage1, garbage2,url;
        while(fp1>>garbage1>>garbage2>>url){
            //cout<<url<<endl;
	    found = domain.find(doubledash);
            string urlcheck = domain.substr(found+2);
		
            if(url.find(urlcheck)!=std::string::npos)
                fp2<<url<<"\n";
        }
    }
    fp1.close();
    fp2.close();
}

