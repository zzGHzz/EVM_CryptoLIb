var Secp256k1 = artifacts.require("Secp256k1");

module.exports = function(deployer) {
    deployer.deploy(Secp256k1);
};