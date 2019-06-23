#!/usr/bin/env node

const path = require("path");
const util = require("util");

const childProcess = require("child_process");
const exec = util.promisify(childProcess.exec);

const [taskName] = process.argv.slice(2);

const buildWebpack = async () => {};
const watchWebpack = async () => {};

const libs = [
  "jest",
  "@glennsl/bs-jest",
  "html-webpack-plugin",
  "bs-platform",
  "webpack",
  "webpack-cli",
  "webpack-dev-server",
].reduce((acc, curr) => `${acc} ${curr}`, "");

const tryFail = async (cb, arg) => {
  try {
    const output = await cb(arg);
    if (output) {
      process.stdout.write(output.stdout);
    }
  } catch (e) {
    console.error("rembrandt cli error: ", e);
    process.exit(1);
  }
};

(async () => {
  switch (taskName) {
    case "build":
      await exec("mkdir -p dist");
      await tryFail(exec, "yarn bsb -make-world");
      await tryFail(exec, "yarn webpack");
      break;
    case "test":
      const jestCli = require("jest/build/jest");
      tryFail(exec, "yarn bsb -make-world");
      await tryFail(jestCli.run);
      break;
    case "start:bs":
      childProcess.exec("yarn bsb -make-world -w").stdout.pipe(process.stdout);
      break;
    case "start:js":
      const webpack = require("webpack");
      const webpackPath = path.join(__dirname, "webpack.config.js");
      const generateWebpackConfig = require(webpackPath);
      childProcess
        .exec("yarn webpack-dev-server --config ./webpack.config.js")
        .stdout.pipe(process.stdout);
      break;
    case "help":
      console.table([
        {
          command: "build",
          description: "compile source file into dist catalog",
          flags: "-"
        },
        { command: "clean", description: "remove all build files", flags: "-" },
        {
          command: "init",
          description: "create seed rembrandt application",
          flags: "-"
        },
        {
          command: "start:bs",
          description: "run buckleScript compilation in watch mode",
          flags: "-"
        },
        {
          command: "start:js",
          description: "run javascript bundler with dev server",
          flags: "-"
        },
        { command: "test", description: "run unit tests", flags: "-" }
      ]);
      break;
    case "init":
      console.log("Rembrandt: start installation");
      await tryFail(exec, "cp -rf ./node_modules/bs-rembrandt/seed/* .");
      await tryFail(
        exec,
        "cp ./node_modules/bs-rembrandt/cli/webpack.config.js ."
      );
      await tryFail(exec, `yarn add ${libs} -dev`);
      console.log("Rembrandt: success");
      break;
    case "clean":
      await tryFail(exec, "rm -rf dist");
      await tryFail(exec, "yarn bsb -clean-world");
      break;
    default:
      console.error("command not found");
      process.exit(1);
  }
})();
