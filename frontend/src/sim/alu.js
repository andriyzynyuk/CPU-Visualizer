export function simulateALU({ x, y, shiftDirection, AddSub, logicFunc, funcClass, constAmount, constVar }) {
        x &= 0b1111;
        y &= 0b1111;
    
        let shiftedY = 0b0000;
        let xorY = 0b0000;
        let xPlusY = 0b0000;
        let logic = 0b0000;
        let carry = 0;
        let s = 0b0000;
        let variableAmount = x & 0b11;
        let amount = 0b00;

        switch(constVar) {
            case 0b0:
                amount = constAmount;
            break;

            case 0b1:
                amount = variableAmount;//2 lsb of x
            break;
        }

        //shifter
        shiftedY = shiftDirection ? (y << amount) : (y >> amount);
        shiftedY &= 0b1111;

        //Adder
        const addSubMask = AddSub ? 0b1111 : 0b0000;
        xorY = y ^ addSubMask;

        const sum = x + xorY + AddSub;
        carry = (sum >> 4) & 1;
        xPlusY = sum & 0b1111;
        
        //Logic Unit
        switch (logicFunc) {
            case 0b00:
                logic = x & y;
            break;

            case 0b01:
                logic = x | y;
            break;

            case 0b10:
                logic = x ^ y;
            break;

            case 0b11:
                logic = ~(x | y) & 0b1111;
            break;
        }

        let msb = xPlusY > 0 ? 0b1111 : 0b0000;

        //Select Output
        switch (funcClass) {
            case 0b00:
                s = shiftedY;
            break;

            case 0b01:
                s = msb;
            break;

            case 0b10:
                s = xPlusY;
            break;

            case 0b11:
                s = logic;
            break;
        }

        s &= 0b1111;

        return {
            inputs: {
                x,
                y,
                shiftDirection,
                AddSub,
                logicFunc,
                funcClass,
                constAmount,
                constVar
            },

            internal: {
                shiftedY,
                xorY,
                xPlusY,
                logic,
                carry,
                variableAmount,
                amount,
                msb
            },

            output: {
            s
            }
        };

}