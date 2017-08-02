#include "process.hpp"
#include <algorithm>

void IProcess::SetChild(ProcessPtr c) {
    child = c;
}


ProcessPtr IProcess::RemoveChild() {
    ProcessPtr ptr;
    std::swap(child, ptr);
    return ptr;
}


IProcess* IProcess::PeekChild() {
    return child.get();
}



void ProcessManager::Update(float dt) {
    for (auto it = processes.begin(); it != processes.end();) {
        IProcess::Status status = (*it)->Update(dt);
        if (status == IProcess::Finished) {
            *it = (*it)->RemoveChild();
            ++it;
        } else if (status == IProcess::Aborted) {
            processes.erase(it);
        }
    }
}


void ProcessManager::QueueProcess(ProcessPtr process) {
    processes.push_back(process);
}


void ProcessManager::RemoveProcess(ProcessPtr process) {
    auto it = std::remove_if(processes.begin(), processes.end(), [&] (const ProcessPtr& ptr) {
        return ptr.get() == process.get();
    });
    processes.erase(it, processes.end());
}


