const hashint = require('..'); // loads ../index.js

describe("Test 'hashint' module", () => {
    describe("Test 'hashint8' method", () => {
        describe("Test method exception causes", () => {
            describe("Should cause 'Expected 2 arguments' exception", () => {
                it("When calling method without any argument", () => {
                    expect(() => {hashint.hashint8();}).toThrow("Expected 1 or 2 arguments.");
                })
            })
            describe("Should cause 'Number expected in first argument' exception", () => {
                it("When passing 'input' value as string", () => {
                    const input = "";
                    const secret = "secret";
                    expect(() => {hashint.hashint8(input,secret);}).toThrow("Number expected in first argument");
                })
                it("When passing 'input' value as array", () => {
                    const input = [];
                    const secret = "secret";
                    expect(() => {hashint.hashint8(input,secret);}).toThrow("Number expected in first argument");
                })
            })
        })
        it("Validate hash lenght to equal 3 characters", () => {
            var input = 13;
            var secret = "secret";
            var hash = hashint.hashint8(input,secret);
            expect(hash.length).toEqual(3);
        })
        describe("Should return valid hash", () => {
            it("When passing 0 as input", () => {
                var input = 0;
                var secret = "secret";
                var hash = hashint.hashint8(input,secret);
                expect(hash).toMatch(/^(\d|[abcdef]){3}$/i);
            })
            it("When passing value less than 0", () => {
                var input = -1;
                var secret = "secret";
                var hash = hashint.hashint8(input,secret);
                expect(hash).toMatch(/^(\d|[abcdef]){3}$/i);
            })
            it("When passing value above 8bit max value", () => {
                var input = 256;
                var secret = "secret";
                var hash = hashint.hashint8(input,secret);
                expect(hash).toMatch(/^(\d|[abcdef]){3}$/i);
            })
        })
    })
    describe("Test 'hashint16' method", () => {
        describe("Test method exception causes", () => {
            describe("Should cause 'Expected 2 arguments' exception", () => {
                it("When calling method without any argument", () => {
                    expect(() => {hashint.hashint16();}).toThrow("Expected 1 or 2 arguments.");
                })
            })
            describe("Should cause 'Number expected in first argument' exception", () => {
                it("When passing 'input' value as string", () => {
                    const input = "";
                    const secret = "secret";
                    expect(() => {hashint.hashint16(input,secret);}).toThrow("Number expected in first argument");
                })
                it("When passing 'input' value as array", () => {
                    const input = [];
                    const secret = "secret";
                    expect(() => {hashint.hashint16(input,secret);}).toThrow("Number expected in first argument");
                })
            })
        })
        it("Validate hash lenght to equal 5 characters", () => {
            var input = 13;
            var secret = "secret";
            var hash = hashint.hashint16(input,secret);
            expect(hash.length).toEqual(5);
        })
        describe("Should return valid hash", () => {
            it("When passing 0 as input", () => {
                var input = 0;
                var secret = "secret";
                var hash = hashint.hashint16(input,secret);
                expect(hash).toMatch(/^(\d|[abcdef]){5}$/i);
            })
            it("When passing value less than 0", () => {
                var input = -1;
                var secret = "secret";
                var hash = hashint.hashint16(input,secret);
                expect(hash).toMatch(/^(\d|[abcdef]){5}$/i);
            })
            it("When passing value above 16bit max value", () => {
                var input = 65536;
                var secret = "secret";
                var hash = hashint.hashint16(input,secret);
                expect(hash).toMatch(/^(\d|[abcdef]){5}$/i);
            })
        })
    })
})