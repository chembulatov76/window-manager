const ADDON_PATH = process.env.NODE_ENV != "dev" ? "Release" : "Debug";

const WindowManager = require(`./build/${ADDON_PATH}/addon`);

module.exports = { WindowManager } ;