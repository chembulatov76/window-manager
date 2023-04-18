let { WindowManager } = require("./");


let hWndChild = Number(process.argv[2]) ?? 0;
let hWndParent = Number(process.argv[3]) ?? 0;

console.log(hWndChild, hWndParent) ;

WindowManager.SetWindowParent(hWndChild, hWndParent);