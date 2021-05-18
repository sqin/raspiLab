#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

void test_temperature_main(){
    DIR *dir;
    struct dirent *dirent;
    char dev[16]={0};
    char devPath[128]={0};
    char buf[256] = {0};
    char tmpData[8] = {0};
    char path[] = "/sys/bus/w1/devices/";
    ssize_t numRead;
    dir = opendir(path);
    if(dir != NULL){
        while ((dirent=readdir(dir)))
        {
            /* code */
            if((dirent->d_type == DT_LNK && strstr(dirent->d_name,"28-") != NULL)){
                strcpy(dev,dirent->d_name);
                //printf("Device:%s\n",dev);
            }
            
        }
        closedir(dir);
    }else{
        perror("could not open the w1 devices directory");
        return ;
    }
    sprintf(devPath,"%s/%s/w1_slave",path,dev);
    //printf("devPath:%s\n",devPath);
    while (1)
    {
        int fd = open(devPath,O_RDONLY);
        if(fd == -1){
            perror("could not open w1 devices");
            return;
        }
        while ((numRead = read(fd,buf,256) > 0 ))
        {
            strncpy(tmpData,strstr(buf,"t=")+2,5);
            float tempC = strtof(tmpData,NULL);
            printf("Device:%s -",dev);
            printf("Temp:%.3f C \n",tempC/1000);
        }
        close(fd);
    }
    return 0;
}

char* getDateTime()
{
	static char nowtime[20];
	time_t rawtime;
	struct tm* ltime;
	time(&rawtime);
	ltime = localtime(&rawtime);
	strftime(nowtime, 20, "%Y-%m-%d %H:%M:%S", ltime);
	return nowtime;
}

float getTemp()
{
    DIR *dir;
    struct dirent *dirent;
    char dev[16] = {0};
    char devPath[128] = {0};
    char buf[256] = {0};
    char tmpData[8] = {0};
    char path[] = "/sys/bus/w1/devices/";
    ssize_t numRead;
    float result;
    dir = opendir(path);
    if (dir != NULL)
    {
        while ((dirent = readdir(dir)))
        {
            /* code */
            if ((dirent->d_type == DT_LNK && strstr(dirent->d_name, "28-") != NULL))
            {
                strcpy(dev, dirent->d_name);
               // printf("Device:%s\n", dev);
            }
        }
        closedir(dir);
    }
    else
    {
        perror("could not open the w1 devices directory");
        return;
    }
    sprintf(devPath, "%s/%s/w1_slave", path, dev);
    //printf("devPath:%s\n", devPath);
    {
        int fd = open(devPath, O_RDONLY);
        if (fd == -1)
        {
            perror("could not open w1 devices");
            return;
        }
        if ((numRead = read(fd, buf, 256) > 0))
        {
            strncpy(tmpData, strstr(buf, "t=") + 2, 5);
            float tempC = strtof(tmpData, NULL);
            //printf("Device:%s -", dev);
            char* nowtime = getDateTime();
            printf("%s Temp:%.3f\n", nowtime,tempC / 1000);
	        fflush(stdout);
            result = tempC/1000;
        }
        close(fd);
    }
    return result;
}
