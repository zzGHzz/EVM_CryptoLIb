const Secp256k1 = artifacts.require("Secp256k1");
const Gx = "0x79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798";
const Gy = "0x483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8";

contract("Secp256k1", accounts => {
    it("should G be on curve", () => {
        let G = [Gx, Gy];
        return Secp256k1.deployed()
            .then(instance => instance.onCurve(G))
            .then(check => {
                assert.equal(check.valueOf(), 1, "G is not on the curve");
            })
    });
});