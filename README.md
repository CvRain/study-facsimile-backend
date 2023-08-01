# study-facsimile-backend
**CVL-Study学习平台，用c++完成的web后端**

# Dependencies
- c++ version += 17
- cmake version += 3.20
- drogon: main web framework
- vcpkg:
  - mongo-c-driver
  - mongo-cxx-driver
  - sqlite3
  - loguru
  - [drogon]

# Directory
- controller: The folder where the controller source files are stored
- filter: The folder where the filter files are stored
- models: The folder of the database model file
  - model.json: not used yet
- services: basically database services like CRUD
- CmakeLists.txt: cpp project configuration file
- config.json: web configuration file provided by drogon (not used yet)
- vcpkg.json: vcpkg package manifest list
- main.cc: program entrance