describe('My First Test', function() {
  it('Does not do much!', function() {
    cy.visit('localhost:3000/basic/index.html');
    cy.get('#count').should('contain', '42');
    cy.get('#plus').click()
    cy.get('#count').should('contain', '43');
    cy.get('#plus').click();
    cy.get('#count').should('contain', '44');
    cy.get('#minus').click();
    cy.get('#count').should('contain', '43');
  })
})