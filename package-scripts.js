const examples = [
  'Basic',
  'Request',
  'Form',
  'Subscription',
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
      default: 'yarn start clean.bs && yarn start clean.server',
      bs: 'bsb -clean-world',
      server: 'rm -rf cypress/server/public',
    },
    server: 'node cypress/server/main.js',
    cy: {
      default: './node_modules/.bin/cypress open',
      run: `./node_modules/.bin/cypress run --spec 'cypress/integration/**'`,
      ci: [
        'yarn start build',
        'yarn start build.examples',
        'yarn start server & (sleep 5 && yarn start cy.run)',
      ].join(' && '),
    },
    ci: [
      'yarn start clean',
      'yarn start build',
      'yarn start test',
      'yarn start build.examples',
    ].join(' && ')
  },
}
