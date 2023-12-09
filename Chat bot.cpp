#include <iostream>
#include <regex>
#include <string>

using namespace std;

string simpleChatbot(const string& userInput) {
    regex hiPattern("(hi|hello|hey).*", regex_constants::icase);
    regex howAreYouPattern("how are you.*", regex_constants::icase);
    regex namePattern("what is your name.*", regex_constants::icase);
    regex byePattern("bye|goodbye.*", regex_constants::icase);
    regex yourNamePattern("(.*) your name(.*)", regex_constants::icase);

    if (regex_match(userInput, hiPattern))
        return "Hello! How can I help you?";
    else if (regex_match(userInput, howAreYouPattern))
        return "I'm just a chatbot, but thanks for asking!";
    else if (regex_match(userInput, namePattern))
        return "I'm a simple chatbot.";
    else if (regex_match(userInput, byePattern))
        return "Goodbye! Have a great day!";
    else if (regex_match(userInput, yourNamePattern))
        return "I'm just a chatbot. You can call me ChatBot.";


    return "I'm sorry, I don't understand that.";
}

int main() {
    cout << "Simple Chatbot: Hi there! Ask me anything or say goodbye to exit." << endl;

    while (true) {
        string userInput;
        cout << "You: ";
        getline(cin, userInput);

        if (userInput == "exit" || userInput == "bye" || userInput == "goodbye") {
            cout << "Simple Chatbot: Goodbye! Have a great day." << endl;
            break;
        }

        string response = simpleChatbot(userInput);
        cout << "Simple Chatbot: " << response << endl;
    }

    return 0;
}
