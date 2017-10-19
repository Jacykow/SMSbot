#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

string message_command(string number, string message){
	string command = "adb shell am start -a android.intent.action.SENDTO -d sms:";
	if(number.length() != 11){
		command+="+48";
	}
	command+=number;
	command+=" --es sms_body ";
	command+='"';
	command+='\'';
	command+=message;
	command+='\'';
	command+='"';
	command+=" --ez exit_on_sent true >nul";
	return command;
}

int main(){
	system("adb unroot");
	
	fstream phone_numbers_data, message_data;
	phone_numbers_data.open("numbers.txt", ios::in);
	message_data.open("message.txt", ios::in);
	
	string message, number;
	getline(message_data, message);
	while(phone_numbers_data >> number){
		cout<<"Message is being send to: "<<number<<endl;
		system(message_command(number,message).c_str());
		
		//to send the first photo in the first album send the following keyevents:
		//22,20,66 (add to the message),22,66 (option "picture from the gallery")
		//20,66 (pick gallery),22,66 (pick photo),19,66 (confirm), follow to send.
		
		//the picture might get resized if its bigger
		//than 300kB for old phones (no research done)
		
		system("adb shell input keyevent 22");
		system("adb shell input keyevent 66");
		system("adb shell input keyevent 4");
		
	}
	
	phone_numbers_data.close();
	message_data.close();
	
	return 0;
}
