#pragma once
#include <vector>
#include <memory>

class IProcess;
typedef std::shared_ptr<IProcess> ProcessPtr;

class IProcess {
public:
    enum Status {
        Running,
        Finished,
        Aborted
    };

    virtual ~IProcess() { }
    virtual Status Update(float dt) = 0;

    void SetChild(ProcessPtr child);
    ProcessPtr RemoveChild();
    IProcess* PeekChild();
private:
    ProcessPtr child;
};


class ProcessManager {
public:

    void Update(float dt);

    void QueueProcess(ProcessPtr process);
    void RemoveProcess(ProcessPtr process);

private:
    std::vector<ProcessPtr> processes;
};

