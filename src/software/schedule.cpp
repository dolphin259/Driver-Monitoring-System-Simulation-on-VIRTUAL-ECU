#include "../../include/schedule.h"

using namespace std;
TaskScheduler::TaskScheduler() : head(nullptr) {}
void TaskScheduler::addTask(int priority, std::string msg) {
    Task* newNode = new Task(priority, msg);
    Task** pp = &head;

    while (*pp != nullptr && (*pp)->priority <= priority) {
        pp = &((*pp)->next);
    }

    newNode->next = *pp;
    *pp = newNode;

    cout << "[Scheduler] Đã thêm tác vụ: " << msg << " (Độ ưu tiên: " << priority << ")\n";
}

void TaskScheduler::run() {
    if (head == nullptr) return;
    cout << "\nĐang thực thi các tác vụ theo thứ tự ưu tiên\n";
    
    while (head != nullptr) {
        Task* temp = head;
        cout << ">> Đang xử lý: " << temp->message << " [Priority: " << temp->priority << "]\n";
        head = head->next;
        delete temp;
    }
}
