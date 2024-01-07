# Opengl-Danmaku

### Danmaku, Bullet hell

**Wikipedia** : "Bullet hell (danmaku, literally "barrage" or "bullet curtain"), also known as manic shooter, is a subgenre of shoot 'em up video games featuring large amounts of projectiles the player character is required to dodge."

#### Project

A `Sandbox` project built with Multithreading support. Objective being that `Core` systems manage their entities concurently for better performance. Additionaly, tooling will be provided to ease the testing process in the creation of complex `Danmaku`.

#### What this README.md is not

Be aware that this project isn't about building a `Game Engine`, explaining `Build system` or `Multithreading`. Even though the aim remains writing good `code`, code architecture might not always respect best practices or be optimized.

## JIRA

**Notes** : Initial step of this project will be to setup the Root for building a single `Entity`, that can be configure from `ImGui` tooling. 

Build system

- [ ] CONFIGURE project Build system through CMake.

Engine

- [x] ADD ImGui submodule
- [x] ADD GLFW submodule
- [x] ADD Glew submodule
- [x] ADD GTEST submodule

- [ ] CONFIGURE basic ENGINE hierarchy.
- [ ] CREATE Core Engine loop

- [ ] CREATE an EntityManager SYSTEM.
- [ ] CREATE an Entity OBJECT.
- [ ] CREATE a Pooling SYSTEM.
- [ ] CREATE a Poolable INTERFACE.

Game

- [ ] CONFIGURE basic GAME hierarchy.

Tooling

- [ ] CREATE an ImGUI Visualizer SYSTEM.
- [ ] ADD functionality to Visualizer so we can parametrize our Entity Movement behaviour

### Danmaku

In this [guide](https://sparen.github.io/ph3tutorials/ddsga2.html), we will discuss the role angles play in bullet movement as well as how bullet graphic choice affects the aesthetics of a pattern, as well as how Bullet Hell games differ from other shmups. 