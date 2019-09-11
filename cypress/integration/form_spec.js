describe('Form example', () => {

  it('2way data binding', () => {
    cy.visit('/Form/index.html');

    cy.get('#first').should('contain', 'first: ');
    cy.get('#second').should('contain', 'second: ');

    cy.get('#first-input').type('John');
    cy.get('#second-input').type('Doe');

    cy.get('#first').should('contain', 'first: John');
    cy.get('#second').should('contain', 'second: Doe');

  });

  it('async loading', () => {
    cy.visit('/Form/index.html');
    cy.get('button').click();

    cy.get('#loading').should('contain', 'loaded');
    cy.wait(500);

    cy.get('#first-input').type('John');
    cy.get('#second-input').type('Doe');

    cy.get('button').click();
    cy.wait(500);
    cy.get('#loading').should('contain', 'loading');
    cy.get('#loading').should('contain', 'loaded');
    cy.get('#response').should('contain', 'response: correct');
  });

  it('send form data to backend', () => {
    cy.visit('/Form/index.html');
    cy.get('button').click();

    cy.get('#loading').should('contain', 'loaded');
    cy.wait(500);

    cy.get('#first-input').type('Mark');
    cy.get('#second-input').type('Doe');

    cy.get('button').click();
    cy.wait(500);
    cy.get('#loading').should('contain', 'loading');
    cy.get('#loading').should('contain', 'loaded');
    cy.get('#response').should('contain', 'response: wrong');
  });

});