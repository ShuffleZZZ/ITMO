import React from 'react';
import {fireEvent, render, RenderResult, screen, waitFor} from '@testing-library/react';
import App from './App';
import Login from './components/Login';
import {MemoryRouter} from 'react-router-dom';
import {chromium, ChromiumBrowser, Page} from "playwright";

const EMAIL = 'asdf@mail.ru';
const PASSWORD = 'asdfgr';

describe('No api tests', () => {
  describe('On render app', () => {

    beforeEach(() => {
      render(<App/>);
    })

    it('has logo', () => {
      const navElement = screen.getByAltText(/logo/);

      expect(navElement).toBeInTheDocument();
    });

    it('has nav bar element', () => {
      const navElement = screen.getByText(/products/i);

      expect(navElement).toBeInTheDocument();
    });
  });

  describe('On render login', () => {

    let component: RenderResult;
    let submitLogin: () => void;
    let fakeUser: { email: string, password: string };
    let emailNode: HTMLInputElement;
    let passwordNode: HTMLInputElement;
    let buttonNode: HTMLInputElement;

    beforeEach(() => {
      submitLogin = jest.fn();

      const props = {
        submitLogin
      };

      component = render(
        <MemoryRouter>
          <Login {...props}/>
        </MemoryRouter>
      );

      fakeUser = {email: EMAIL, password: PASSWORD};
      emailNode = component.getByPlaceholderText('Email') as HTMLInputElement;
      passwordNode = component.getByPlaceholderText('Password') as HTMLInputElement;
      buttonNode = component.getByText('Login') as HTMLInputElement;

      fireEvent.change(emailNode, {target: {value: fakeUser.email}});
      fireEvent.change(passwordNode, {target: {value: fakeUser.password}});

      fireEvent.click(buttonNode);
    })

    it('is form submitted', async () => {
      await waitFor(() => {
        expect(submitLogin).toHaveBeenCalledTimes(1);
      });
    });
  });
});

describe('playwright e2e', () => {
  const DEFAULT_ROUTE = 'http://localhost:3000';

  let browser: ChromiumBrowser;
  let page: Page;

  beforeEach(async () => {
    browser = await chromium.launch();
    page = await browser.newPage();

    if (!page) {
      throw new Error("Connection wasn't established");
    }
  });

  afterEach(async () => {
    await browser.close();
  });

  it('home page loaded', async () => {
    await page.goto(DEFAULT_ROUTE);
    expect(await page.innerText('.description')).toBe('insert your inspiring tagline here');
  });

  it('unexpected route', async () => {
    await page.goto(`${DEFAULT_ROUTE}/pool`);
    const onlyNav = /^<nav>.*?<\/nav>$/.test(await page.innerHTML('.App'));
    expect(onlyNav).toBeTruthy();
  });

  describe('auth check', () => {

    beforeEach(async () => {
      await page.goto(`${DEFAULT_ROUTE}/login`);
      await page.fill('#input-email', EMAIL);
      await page.fill('#input-password', PASSWORD);
      await page.click('.form_button');
    });

    it('auth success', async () => {
      expect(await page.innerText('.title')).toBe('You are logged in');
    });

    it('logout success', async () => {
      await page.goto(`${DEFAULT_ROUTE}/success`);
      await page.click('.form_button');
      const loggedOut = /Login/.test(await page.innerText('.nav-links'));
      expect(loggedOut).toBeTruthy();
    });
  });

  it('auth fail', async () => {
    await page.goto(`${DEFAULT_ROUTE}/login`);
    await page.fill('#input-email', EMAIL);
    await page.fill('#input-password', `${PASSWORD}s`);
    await page.click('.form_button');

    expect(await page.innerText('.title')).toBe('Failed to login');
  });
});
