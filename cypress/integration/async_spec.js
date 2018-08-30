describe('Basic example', () => {

  it('counter should be increased 2x after click on #double', () => {
    cy.visit('localhost:3000/async/index.html');
    cy.get('#count').should('contain', '42');
    cy.get('#double').click();
    cy.get('#count').should('contain', '44');
  });

});