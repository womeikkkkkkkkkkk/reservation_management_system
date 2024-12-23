#pragma once
#include "Identity.h"

void Identity::setName(const std::string& name)//
{
    this->name = name;
}

void Identity::setPassward(const std::string& passward)
{
    this->passward = passward;
}

void Identity::setStatus(bool status)
{
    this->status = status;
}

int Identity::getId() const
{
    return this->id;
}

std::string Identity::getName()const
{
    return this->name;
}

std::string Identity::getPassward() const
{
    return this->passward;
}

bool Identity::getStatus()const
{
    return this->status;
}