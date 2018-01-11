# cocos2d-x-additions

![gif](https://github.com/Tymonrare/cocos2d-x-additions/blob/master/misc/doc/demo.gif?raw=true)

- lot of JSB binding examples
- box2d jsb bindings
- [R.U.B.E.](https://www.iforce2d.net/rube/) scene and JS bindings
- All symlinks in this project has absolute paths. It wrong, i'll fix it soon
- sprite mesh-grid generator
- Surface texture generator(In progress for now). My point about this - tileMaps is too old and we need some better solution by default - like [Joe Russ](https://twitter.com/Mografi_Joe/status/872239807921086464) showed
- It has lot of problems with building

- Tested only on linux

## Build
 - It REALLY hard to run first because of lot JSB issues
 - First of all you have to build box2d manually and copy it in any $PATH path(Because binding-generator causes error if box2d will try to build in Make)
 - Next you have to install all [binding-generator](https://github.com/cocos2d/bindings-generator) requirements
 - now you may try to run ./fullrun.sh

## TODO

- [Rope class](https://pixijs.github.io/examples/#/basics/textured-mesh.js)
- Make build process easer
