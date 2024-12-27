#include "ComputerRoomManager.h"

void ComputerRoomManager::addComputerRoom(const ComputerRoomDTO& computerRoom) {
    try {
        if (computerRoom.getId().empty()) {
            throw std::invalid_argument("机房编号不能为空");
        }
        if (computerRoom.getMax().empty()) {
            throw std::invalid_argument("最大容量不能为空");
        }
        computerroomDAO.addComputerRoom(computerRoom);
        std::cout << "机房：" << computerRoom.getId() << "添加成功" << std::endl;
    }
    catch (std::exception& e) {
        std::string s = "添加机房失败" + std::string(e.what());
        std::cerr << s << std::endl;
        ExceptionLog::GetInstance()->LogException(s);
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void ComputerRoomManager::deleteComputerRoom(const std::string& computerroomid) {
    try {
        if (computerroomid.empty()) {
            throw std::invalid_argument("机房编号不能为空");
        }
        computerroomDAO.deleteComputerRoom(computerroomid);
        std::cout << "机房 " << computerroomid << " 删除成功" << std::endl;
    }
    catch (const std::exception& e) {
        std::string s = "删除机房失败: " + std::string(e.what());
        std::cerr << s << std::endl;
        ExceptionLog::GetInstance()->LogException(s);
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void ComputerRoomManager::updateComputerRoom(const ComputerRoomDTO& computerRoom) {
    try {
        if (computerRoom.getId().empty()) {
            throw std::invalid_argument("机房编号不能为空");
        }
        if (computerRoom.getMax().empty()) {
            throw std::invalid_argument("最大容量不能为空");
        }
        computerroomDAO.updateComputerRoom(computerRoom);
        std::cout << "机房 " << computerRoom.getId() << " 更新成功" << std::endl;
    }
    catch (const std::exception& e) {
        std::string s = "更新机房失败: " + std::string(e.what());
        std::cerr << s << std::endl;
        ExceptionLog::GetInstance()->LogException(s);
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

std::vector<ComputerRoomDTO> ComputerRoomManager::getAllComputerRooms() {
    try {
        std::vector<ComputerRoomDTO> rooms = computerroomDAO.getAllComputerRooms();
        return rooms;
    }
    catch (const std::exception& e) {
        std::string s = "获取所有机房失败: " + std::string(e.what());
        std::cerr << s << std::endl;
        ExceptionLog::GetInstance()->LogException(s);
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

ComputerRoomDTO ComputerRoomManager::getComputerRoom(const std::string& computerroomid) {
    try {
        if (computerroomid.empty()) {
            throw std::invalid_argument("机房编号不能为空");
        }
        ComputerRoomDTO room = computerroomDAO.getComputerRoom(computerroomid);
        return room;
    }
    catch (const std::exception& e) {
        std::string s = "获取机房失败: " + std::string(e.what());
        std::cerr << s << std::endl;
        ExceptionLog::GetInstance()->LogException(s);
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}