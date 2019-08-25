describe('Form example', () => {

  it('Counter should increase', () => {
    cy.visit('/Subscription/index.html');
    cy.get('#count').should('contain', '42');
    cy.get('#count').should('contain', '43');
    cy.get('#count').should('contain', '44');
    cy.get('#count').should('contain', '45');
    cy.get('#count').should('contain', '46');
    cy.get('#count').should('contain', '47');
    cy.get('#count').should('contain', '48');
    cy.get('#count').should('contain', '49');
  });

});
