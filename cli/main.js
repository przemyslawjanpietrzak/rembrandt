const util = require("util");
const chalk = require("chalk");

const jestCli = require("jest/build/jest");

const webpack = require("webpack");

const childProcess = require("child_process");
const exec = util.promisify(childProcess.exec);

const generateWebpackConfig = require("./webpack.config");
const [taskName] = process.argv.slice(2);

const buildWebpack = async () => {};
const watchWebpack = async () => {};

const tryFail = async (cb, arg) => {
  try {
    const output = await cb(arg);
    if (output) {
      process.stdout.write(output.stdout);
    }
  } catch (e) {
    console.error("rembrandt cli error: ", e); // TODO: colors
    process.exit(1);
  }
};

const runWebpack = util.promisify(() =>
  webpack(generateWebpackConfig({ port: 4200, isProduction: false })));

(async () => {
  switch (taskName) {
    case "build":
      await exec("mkdir -p dist");
      tryFail(exec, "npx bsb -make-world");
      break;
    case "test":
      tryFail(exec, "npx bsb -make-world");
      await tryFail(jestCli.run);
      break;
    case "start:bs":
      childProcess.exec("npx bsb -make-world -w").stdout.pipe(process.stdout);
      // await runWebpack();
      break;
    case 'start:js':
      childProcess.exec("npx webpack-dev-server --config ./cli/webpack.config.js").stdout.pipe(process.stdout);
      // await runWebpack();
      break;
    case "help":
      break;
    case "clean":
      await tryFail(exec, "rm -rf dist");
      await tryFail(exec, "npx bsb -clean-world");
      break;
    default:
      console.error("command not found");
      process.exit(1);
  }
})();
