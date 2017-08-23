# cocos2d-x-additions

- lot of JSB binding examples
 - box2d jsb bindings
- All symlinks in this project has absolute paths. It wrong, i'll fix it soon
- sprite mesh generator
- Surface generator
- It has lot of problems with building

- Tested only on linux

## Build
 - It REALLY hard to run first because of lot JSB issues
 - First of all you have to build box2d manually and copy it in any $PATH path(Because binding-generator causes error if box2d will try to build in Make)
 - Next you have to install all [binding-generator](https://github.com/cocos2d/bindings-generator) requirements
 - now you may try to run ./fullrun.sh
