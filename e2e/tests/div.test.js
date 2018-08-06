// const { host, height, width, headless } = require('../settings');

// let page;
// let browser;

beforeEach(async () => {
  // browser = await puppeteer.launch({
  //   headless,
  //   args: [`--window-size=${width},${height}`, '--no-sandbox'],
  // });
  // page = await browser.newPage();

  // await page.goto(host);
  // await page.setViewport({ height, width });
});

afterEach(() => {
  // browser.close();
});

test('login and logout', async () => {
  // const children = await page.evaluate(() => document.querySelector('#app').children);
  // assert(children.length).toBe(5);
});