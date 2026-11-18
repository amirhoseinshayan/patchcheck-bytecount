# Bytecount fixture independent reference
This reference was defined from the intended fixture contract, not captured
from a candidate executable; it is a harmless framework self-test.

## accepted
For every byte string of length 0–1024 whose first byte is not `!`, stdout is
exactly `OK\n`, stderr is empty, and exit code is zero. This rule applies to
binary data and every minimized input. MARK/OTHER are intentionally defective
fixture behavior, not exceptions in this independent reference.

## invalid
Length greater than 1024 or a leading `!` produces no stdout, `invalid\n` on
stderr and exit 2. Inputs are stdin, file bytes, or a UTF-8 argv string without
NUL. The fixture is bounded and contains no intended memory vulnerability.
