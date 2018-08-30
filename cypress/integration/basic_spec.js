describe('Basic example', () => {

  it('counter should be increased after click on #plus', () => {
    cy.visit('localhost:3000/basic/index.html');
    cy.get('#count').should('contain', '42');
    cy.get('#plus').click()
    cy.get('#count').should('contain', '43');
    cy.get('#plus').click();
  });

  it('counter should be increased after click on #plus', () => {
    cy.visit('localhost:3000/basic/index.html');
    cy.get('#count').should('contain', '42');
    cy.get('#count').should('contain', '44');
    cy.get('#minus').click();
    cy.get('#count').should('contain', '43');
    cy.get('#minus').click();
    cy.get('#count').should('contain', '42');
  });

});