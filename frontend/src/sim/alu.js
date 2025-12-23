export function simulateALU({ x, y, shiftDirection, AddSub, logicFunc, funcClass }) {
        x &= 0b1111;
        y &= 0b1111;
    
        let shiftedY = 0b0000;
        let xorY = 0b0000;
        let xPlusY = 0b0000;
        let logic = 0b0000;
        let carry = 0;
        let s = 0b0000;

        //shifter
        shiftedY = shiftDirection ? (y << 1) : (y >> 1);
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

        //Select Output
        switch (funcClass) {
            case 0b00:
                s = shiftedY;
            break;

            case 0b01:
                s = carry ? 0b1111 : 0b0000;
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
                funcClass
            },

            internal: {
                shiftedY,
                xorY,
                xPlusY,
                logic,
                carry
            },

            output: {
            s
            }
        };

}