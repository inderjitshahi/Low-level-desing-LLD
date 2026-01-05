#include <iostream>
#include <string>
#include <stack>
using namespace std;

class TextEditor {
private:
    string text;

public:
    void insert(int position, const string& str) {
        text.insert(position, str);
    }

    void erase(int position, int length) {
        text.erase(position, length);
    }

    string getText() const {
        return text;
    }
};

class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual void undo() = 0;
};


class InsertTextCommand : public Command {
private:
    TextEditor* editor;
    string text;
    int position;

public:
    InsertTextCommand(TextEditor* ed, int pos, const string& txt)
        : editor(ed), position(pos), text(txt) {}

    void execute() override {
        editor->insert(position, text);
    }

    void undo() override {
        editor->erase(position, text.length());
    }
};

class DeleteTextCommand : public Command {
private:
    TextEditor* editor;
    string deletedText;
    int position;

public:
    DeleteTextCommand(TextEditor* ed, int pos, int length)
        : editor(ed), position(pos) {
        deletedText = editor->getText().substr(pos, length);
    }

    void execute() override {
        editor->erase(position, deletedText.length());
    }

    void undo() override {
        editor->insert(position, deletedText);
    }
};



class CommandManager {
private:
    stack<Command*> undoStack;
    stack<Command*> redoStack;

public:
    void executeCommand(Command* cmd) {
        cmd->execute();
        undoStack.push(cmd);

        // Clear redo stack on new action
        while (!redoStack.empty())
            redoStack.pop();
    }

    void undo() {
        if (undoStack.empty()) return;

        Command* cmd = undoStack.top();
        undoStack.pop();
        cmd->undo();
        redoStack.push(cmd);
    }

    void redo() {
        if (redoStack.empty()) return;

        Command* cmd = redoStack.top();
        redoStack.pop();
        cmd->execute();
        undoStack.push(cmd);
    }
};



int main() {
    TextEditor editor;
    CommandManager manager;

    manager.executeCommand(new InsertTextCommand(&editor, 0, "Hello"));
    manager.executeCommand(new InsertTextCommand(&editor, 5, " World"));

    cout << editor.getText() << endl;  // Hello World

    manager.undo();
    cout << editor.getText() << endl;  // Hello

    manager.redo();
    cout << editor.getText() << endl;  // Hello World

    manager.executeCommand(new DeleteTextCommand(&editor, 5, 6));
    cout << editor.getText() << endl;  // Hello

    manager.undo();
    cout << editor.getText() << endl;  // Hello World
}

