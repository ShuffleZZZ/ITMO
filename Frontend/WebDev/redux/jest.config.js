module.exports = {
  preset: 'ts-jest',
  testEnvironment: 'node',
  collectCoverageFrom: ['src/**/*.ts'],
  testMatch: ['**/test/?(*.)+(spec|test).[jt]s?(x)']
};
