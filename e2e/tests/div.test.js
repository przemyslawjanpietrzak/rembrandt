const puppeteer = require('puppeteer');
const { host, height, width, headless } = require('../settings');

let page;
let browser;

beforeEach(async () => {
  browser = await puppeteer.launch({
    headless,
    args: [`--window-size=${width},${height}`, '--no-sandbox'],
  });
  page = await browser.newPage();

  await page.goto(host);
  await page.setViewport({ height, width });
});

afterEach(() => {
  browser.close();
});

test('', async () => {
  await page.waitForSelector('#app > div')
  const childrenCount = await page.evaluate(() => document.querySelector('#app > div').children.length);
  expect(childrenCount).toBe(5);
});