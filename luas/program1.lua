-- program1.lua
local program1 = {}

program1.global_val = nil

function program1.called(passedString)
    print(passedString)
    passedString = passedString .. " " .. "Edited"
    -- global_val edited from the C program
    print(program1.global_val)
    return passedString
end