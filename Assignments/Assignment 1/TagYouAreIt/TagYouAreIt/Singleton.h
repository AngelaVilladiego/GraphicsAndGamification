#pragma once

#ifndef SINGLETON_H
#define SINGLETON_H

// thread safe singleton template
// avoids holding onto copies of deleted instances by overloading the = operator

template <typename T>
class Singleton
{
public:
	static T& GetInstance()
	{
		static T instance;
		return instance;
	}

protected:
	Singleton() {} //constructor
	virtual ~Singleton() {} //destructor, virtual is important for cases where you might have a hierarchy of classes derived from Singleton, and each derived class needs to clean up its resources properly.

public:
	Singleton(Singleton const&) = delete; //copy constructor marked as delete, explicitly disabled. Cannot create new instances through copy constructor
	Singleton& operator=(Singleton const&) = delete; //assignment operator marked as delete, explicitly disabled. Cannot create new instances through = operator.
};

#endif // SINGLETON_H