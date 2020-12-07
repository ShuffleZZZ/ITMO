require("dotenv").config({ silent: true });

module.exports = {
  port: 3000,
  env: "development",
  db: {
    dialect: "sqlite",
    storage: ":memory:"
  }
};
