module.exports = {
  parserOptions: {
    ecmaVersion: 8
  },
  extends: ['@yandex-lms-ext/eslint-config-base'],
  env: {
    es6: true,
    jest: true,
    node: true
  },
  rules: {
    'import/no-extraneous-dependencies': [
      2,
      {
        devDependencies: ['**/*.spec.js']
      }
    ]
  }
};
