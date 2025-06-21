
// alu.v - ALU module

module alu #(parameter WIDTH = 32) (
    input       [WIDTH-1:0] a, b,       // operands         
    input [2:0]     funct3,             //function3
    input           funct7b5,           //for srl vs sra
    input       [2:0] alu_ctrl,         // ALU control
    output reg  [WIDTH-1:0] alu_out,    // ALU output
    output      zero                    // zero flag
);

always @(a, b, alu_ctrl,funct3,funct7b5) begin
    case (alu_ctrl)
        3'b000:  alu_out = a + b;           // ADD
        3'b001:  alu_out = a - b;           // SUB
        3'b010:  alu_out = a & b;           // AND
        3'b011:  alu_out = a | b;           // OR
        3'b100:  alu_out = a << b[4:0];     // SLL
        3'b101: 
            alu_out = (funct3 == 3'b010) ? 
                      ((a[WIDTH-1] != b[WIDTH-1]) ? a[WIDTH-1] : (a < b)) : ($unsigned(a) < $unsigned(b)); // SLTU
        3'b110:
					if(funct7b5) alu_out = ($signed(a) >>> b[4:0]); //SRA
					else alu_out = (a >> b[4:0]); // SRL
        3'b111:  alu_out = a ^ b; // XOR
        default: alu_out = 0;
    endcase
end

assign zero = (alu_out == 0) ? 1'b1 : 1'b0;

endmodule

