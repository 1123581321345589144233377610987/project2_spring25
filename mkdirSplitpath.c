#include "types.h"

extern struct NODE* root;
extern struct NODE* cwd;

//make directory
void mkdir(char pathName[]){
    if(!(strcmp(pathName, "/"))){
        printf("MKDIR ERROR: no path provided\n");
        return;
    }
    
    //allocate space for all the strings
    char baseName[64];
    char dirName[64];
    struct NODE* currNode=splitPath(pathName,baseName,dirName);
    struct NODE* newNode = (struct NODE*)malloc(sizeof(struct NODE));
    if(currNode==NULL){
        return;
    }
    struct NODE* childNode = currNode->childPtr;
    while(childNode!=NULL){
        if(!(strcmp(childNode->name,baseName))){
            printf("MKDIR ERROR: directory %s already exists\n",baseName);
            return;
        }
        childNode=childNode->siblingPtr;
    }
    
    newNode->fileType='D';
    strncpy(newNode->name,baseName,strlen(baseName));
    newNode->name[strlen(baseName)]='\0';
    newNode->childPtr=NULL;
    newNode->siblingPtr=NULL;
    newNode->parentPtr=NULL;
    if(currNode->childPtr==NULL){
        currNode->childPtr=newNode;
    }
    else{
        childNode=currNode->childPtr;
        while(childNode->siblingPtr!=NULL){
            childNode=childNode->siblingPtr;
        }
        childNode->siblingPtr=newNode;
    }
    newNode->parentPtr=currNode;
    printf("MKDIR SUCCESS: node %s successfully created\n",baseName);
    return;
    
}

//handles tokenizing and absolute/relative pathing options
struct NODE* splitPath(char* pathName, char* baseName, char* dirName){
    for(int i=strlen(pathName)-1;i>=0;i--){
//setting dirName and baseName
        if(i==0 || (i > 0 && pathName[i - 1] == '/')){
            for(unsigned int j=i;j<strlen(pathName);j++){
                baseName[j-i]=pathName[j];
            }
            baseName[strlen(pathName)-i]='\0';
            if(i>1){
                for(unsigned int k=0;k<i-1;k++){
                    dirName[k]=pathName[k];
                }
                dirName[i-1]='\0';
            }
            else{
                dirName[0]='\0';
            }

//initializing current node and child node
            struct NODE* childNode=(struct NODE*)malloc(sizeof(struct NODE));
            childNode=NULL;
            struct NODE* currNode=(struct NODE*)malloc(sizeof(struct NODE));
            currNode=NULL;
            if(pathName[0]=='/'){
                currNode=root;
            }
            else{
                currNode=cwd;
            }

//initializing current directory name
            char dirCopy[strlen(dirName) + 1];
            strcpy(dirCopy, dirName);
            char* currDirName = strtok(dirCopy, "/");

            while(currDirName != NULL){
                childNode = currNode->childPtr;
                while(childNode!=NULL){
                    if (strcmp(childNode->name,currDirName)==0) {
                        break;
                    }
                    childNode = childNode->siblingPtr;
                }

                if (childNode==NULL){
                        printf("ERROR: directory %s does not exist \n", currDirName);
                        return NULL;
                }
                currNode = childNode; // we traverse the tree to the next depth with this assignment
                currDirName = strtok(NULL,"/"); 
            }
            return currNode;
        }
    }
    return NULL;
}
    // TO BE IMPLEMENTED
    // NOTE THAT WITHOUT COMPLETING THIS FUNCTION CORRECTLY
    // rm, rmdir, ls, cd, touch COMMANDS WILL NOT EXECUTE CORRECTLY
    // SEE THE PROVIDED SOLUTION EXECUTABLE TO SEE THEIR EXPECTED BEHAVIOR

    // YOUR CODE HERE
    //
