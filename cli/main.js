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

(async () => {
  switch (taskName) {
    case "build":
      await exec("mkdir -p dist");
      await tryFail(exec, 'npx bsb -make-world');
      await tryFail(exec, 'npx webpack --config ./cli/webpack.config.js');
      break;
    case "test":
      tryFail(exec, "npx bsb -make-world");
      await tryFail(jestCli.run);
      break;
    case "start:bs":
      childProcess.exec("npx bsb -make-world -w").stdout.pipe(process.stdout);
      break;
    case 'start:js':
      childProcess.exec("npx webpack-dev-server --config ./cli/webpack.config.js").stdout.pipe(process.stdout);
      break;
    case "help":
      console.table([
        { command: 'build', description: 'compile source file into dist catalog', flags: '-' },
        { command: 'clean', description: 'remove all build files', flags: '-' },
        { command: 'init', description: 'create seed rembrandt application', flags: '-' },
        { command: 'start:bs', description: 'run buckleScript compilation in watch mode', flags: '-' },
        { command: 'start:js', description: 'run javascript bundler with dev server', flags: '-' },
        { command: 'test', description: 'run unit tests', flags: '-' },
    ]);
      break;
    case "init":
      await tryFail(exec, 'cp -rf ./node_modules/rembrandt/seed/* .');
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
