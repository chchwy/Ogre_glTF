#pragma once

#include <memory>
#include <Ogre.h>

#include "Ogre_glTF_DLL.hpp"



//Forward declare main class
class Ogre_glTF;

///Class that hold the loaded content of a glTF file and that can create Ogre objects from it
class Ogre_glTF_EXPORT Ogre_glTF_adapter
{
	friend class Ogre_glTF;

	///Private constructor. Ogre_glTF act as a factory for theses object.
	///This will aslo initialize the "pimpl" structure
	Ogre_glTF_adapter();

	///opaque content of the class
	struct impl;

	///pointer to implementation
	std::unique_ptr<Ogre_glTF_adapter::impl> pimpl;

public:
	///This clear the pimpl structure
	~Ogre_glTF_adapter();

	///Deleted copy constructor : non copyable class
	Ogre_glTF_adapter(const Ogre_glTF_adapter&) = delete;

	///Deleted asignment constructor : non copyable class
	Ogre_glTF_adapter& operator=(const Ogre_glTF_adapter&) = delete;

	///Construct an item for this object
	/// \param smgr pointer to the scene manager where we are creating the item
	Ogre::Item* getItem(Ogre::SceneManager* smgr) const;

	///Move constructor : object is movable
	/// \param other object to move
	Ogre_glTF_adapter(Ogre_glTF_adapter&& other) noexcept;

	///Move assignemnt operator
	Ogre_glTF_adapter& operator=(Ogre_glTF_adapter&& other) noexcept;

	///Return the current state of the adapter
	bool isOk() const;

	///Return the last error generated by the underlying glTF loading library
	std::string getLastError() const;
};

///Class that is responsible for initializing the library with the loader, and giving out
class Ogre_glTF_EXPORT Ogre_glTF
{
	///object that acutally communicate with the underlying glTF loading library
	struct gltfLoader;

	///Opaque pointer that handle the underlying glTF loading library (pimpl)
	std::unique_ptr<Ogre_glTF::gltfLoader> loaderImpl;

public:
	///Initialize the library by creating this object.
	Ogre_glTF();

	///Move constructor
	/// \param other object to move
	Ogre_glTF(Ogre_glTF&& other) noexcept;

	///Deinitialize the library at this object destruction
	~Ogre_glTF();

	///Load a glTF text or binary file. Give you an adapter to use this file with Ogre
	/// \param path String containing the path to a file to load (either .glTF or .glc)
	Ogre_glTF_adapter loadFile(const std::string& path) const;

	///Deleted copy contructor
	Ogre_glTF(const Ogre_glTF&) = delete;

	///Deleted asignment operator
	Ogre_glTF& operator=(const Ogre_glTF&) = delete;
};
