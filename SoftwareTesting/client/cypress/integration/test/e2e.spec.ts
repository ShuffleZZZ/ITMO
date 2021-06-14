const DEFAULT_ROUTE = 'http://localhost:3000';
const EMAIL = 'asdf@mail.ru';
const PASSWORD = 'asdfgr';

describe('cypress e2e', () => {
  it('home page loaded', () => {
    cy.visit(DEFAULT_ROUTE);
    cy.get('.description').should('contain', 'insert your inspiring tagline here');
  });

  it('unexpected route',  () => {
    cy.visit(`${DEFAULT_ROUTE}/pool`);
    cy.get('.App').should('not.contain', 'main');
  });

  it('auth and logout success', () => {
    cy.visit(`${DEFAULT_ROUTE}/login`);
    cy.get('#input-email').click({force: true});
    cy.wait(100);
    cy.get('#input-email').type(EMAIL);
    cy.wait(100);
    cy.get('#input-password').click({force: true});
    cy.wait(100);
    cy.get('#input-password').type(PASSWORD);
    cy.wait(100);
    cy.get('.form_button').click();
    cy.wait(100);
    cy.get('.nav-links').should('contain', /(.*?)@.*/.exec(EMAIL)!![1]);

    cy.visit(`${DEFAULT_ROUTE}/success`);
    cy.get('.form_button').click();
    cy.wait(1000);
    cy.get('.nav-links').should('contain', 'Login');
  });

  describe('auth fail', () => {
    it('auth fail', () => {
      cy.visit(`${DEFAULT_ROUTE}/login`);
      cy.get('#input-email').click({force: true});
      cy.wait(100);
      cy.get('#input-email').type(EMAIL);
      cy.wait(100);
      cy.get('#input-password').click({force: true});
      cy.wait(100);
      cy.get('#input-password').type(`${PASSWORD}s`);
      cy.wait(100);
      cy.get('.form_button').click();
      cy.wait(100);
      cy.get('.title').should('contain', 'Failed to login');
    });
  });
});
