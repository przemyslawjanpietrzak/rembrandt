
describe('Basic example', () => {

  it('app should send request and display data from it', () => {
    cy.server({ delay: 1500 })
    cy.route('GET', 'localhost:3000/api/example/1', {})

    cy.visit('/Request/index.html');
    cy.get('#data').should('contain', 'begin');
    cy.get('#request').click();
    cy.get('#data').should('contain', 'loading');
    cy.wait(5000)
    cy.get('#data').should('contain', 'example string #1');
  });
});