// #include"../head/mainhead.h"
 
// void m_play(std::vector<Note>& notes){
//         std::cout << "\n  播放中... (按任意键停止)\n";
//         playNotes(notes);
//         std::cout<<"按任意键以继续..."<<std::endl;
//         _getch();//等待用户输入
// }

// void m_set_sheet(std::string* sheet){
//     std::cout << "\n  输入新曲谱: ";
//     std::string user_in;
//     std::getline(std::cin,user_in);
//     std::transform(user_in.begin(),user_in.end(),user_in.begin(),toupper);
//     if(user_in!="RETURN"){
//         (*sheet)=user_in;// 就是喜欢加括号，没办法捏
//     }
// }
// void m_exit(){
//     exit(0);
// }
// void m_help(){
//     std::cout<<"\nCtrl+Alt+Shift+S可以暂停音乐哦\n其他的没写(\n";
//     std::cout<<"按任意键以继续..."<<std::endl;
//     _getch();//等待用户输入
// }

// void m_default(){
//         std::cout << "\n  无效选项，重新选择\n";
//         Sleep(1000);
// }