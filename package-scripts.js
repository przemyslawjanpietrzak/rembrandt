const examples = [
  'Basic',
  'Request',
  'Form',
];
const buildExample = name => [
  `mkdir -p cypress/server/public/${name}`,
  `cp examples/index.html cypress/server/public/${name}/`,
  `browserify --entry=examples/${name}.bs.js --outfile=cypress/server/public/${name}/index.js`,
].join(' && ');

module.exports = {
  scripts: {
    default: 'bsb -make-world -w',
    build: {
      default: 'bsb -make-world',
      examples: examples.map(buildExample).join(' && '),
    },
    test: {
      default: 'jest __tests__ __tests__/**/*.bs.js',
      e2e: {
        script: `node cypress/server/main.js & ./node_modules/.bin/cypress run --spec 'cypress/integration/**'`
      }
    },
    clean: {
      default: 'npm start clean.bs && npm start clean.server',
      bs: 'bsb -clean-world',
      server: 'rm -rf cypress/server/public',
    },
    server: 'node cypress/server/main.js',
    cy: {
      default: './node_modules/.bin/cypress open',
      run: `./node_modules/.bin/cypress run --spec 'cypress/integration/**'`,
    },
    ci: [
      'npm start clean',
      'npm start build',
      'npm start test',
      'npm start build.examples',
      'npm start server & (sleep 5 && npm start cy.run)'
    ].join(' && ')
  },
}
