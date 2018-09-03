const examples = [
  'Basic',
  'Request',
  'Form',
];
const buildExample = name => [
  `mkdir -p cypress/server/public/${name}`,
  `cp examples/index.html cypress/server/public/${name}/`,
  `fpack examples/${name}.bs.js --output=cypress/server/public/${name}`,
].join(' && ');

module.exports = {
  scripts: {
    default: 'bsb -make-world -w',
    build: {
      default: 'bsb -make-world',
      examples: examples.map(buildExample).join(' && '),
    },
    test: {
      default: 'jest __tests__',
      e2e: {
        script: `node cypress/server/main.js & ./node_modules/.bin/cypress run --spec 'cypress/integration/**'`
      }
    },
    clean: {
      default: 'npm start clean.bs && npm start clean.server',
      bs: 'bsb -clean-world',
      server: 'rm -rf cypress/server/public',
    },
  },
}