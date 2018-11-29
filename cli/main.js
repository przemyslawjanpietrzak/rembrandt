const util = require('util');
const chalk = require('chalk');

const jestCli = require('jest/build/jest');

const exec = util.promisify(require('child_process').exec);

const [taskName] = process.argv.slice(2);

const buildWebpack = async () => {};
const watchWebpack = async () => {};


const tryFail = async (cb, arg) => {
  try {
    const output = await cb(arg);
    console.log(output);
  } catch (e) {
    console.error('rembrandt cli error: ', e);
    process.exit(1);
  }
}

const buildBSP = async () => {};
const watchBSP = async () => {};

(async () => {
  switch(taskName) {
    case 'build':
      await exec('mkdir -p dist');
      await buildWebpack();
      break;
    case 'test':
      await tryFail(buildBSP);
      await tryFail(jestCli.run);
      break;
    case 'start':
      await tryFail(exec, 'cat xxx.json');
      break;
    case 'help':
      break;
    case 'clean':
      const { stdout, stderr } = await exec('rm -rf dist');
      if (!stderr) console.log('catalog dir has been removed');
      else console.error(`Error: ${stderr}`);
      break;
    case 'lint':
      break;
    default:
      console.error('command not found');
      process.exit(1);
  }
})()  

