describe('Basic example', () => {

  it('counter should be increased after click on #plus', () => {
    cy.visit('localhost:3000/basic/index.html');
    cy.get('#count').should('contain', '42');
    cy.get('#plus').click()
    cy.get('#count').should('contain', '43');
    cy.get('#plus').click();
  });

  it('counter should be decrease after click on #minus', () => {
    cy.visit('localhost:3000/basic/index.html');
    cy.get('#count').should('contain', '42');
    cy.get('#minus').click();
    cy.get('#count').should('contain', '41');
    cy.get('#minus').click();
    cy.get('#count').should('contain', '40');
  });

  it('counter should be increased 2x after click on #double', () => {
    cy.visit('localhost:3000/basic/index.html');
    cy.get('#count').should('contain', '42');
    cy.get('#double').click();
    cy.wait(5000)
    cy.get('#count').should('contain', '44');
  });

});