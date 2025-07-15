import subprocess

def run_echo(input_data):
    process = subprocess.Popen(
        ['x64/Debug/Interpreter.exe'],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
#        encoding='utf-8'
    )
    stdout, stderr = process.communicate(input_data)
    return stdout.strip(), stderr.strip()

def test_echo():
    tests = [
        {"input": "5 + 3 * 2\n", "expected_output": "11"},
        {"input": "max(5, 2)\n", "expected_output": "5"},
        {"input": "max(min(3 * 2, 2), 2)\n", "expected_output": "2"},
        {"input": "def myfunc(a, b) { min(a, b) + max(a, b) }\n", "expected_output": ""},
        {"input": "def myfunc(a, b) { min(a, b) + max(a, b) }\nmyfunc(3, 4)\n", "expected_output": "7"}
    ]

    for test in tests:
        input_data = test["input"] + 'exit\n'
        expected_output = test["expected_output"]
        output, error = run_echo(input_data)

        if error:
            print(f"❌ Test failed for input:\n{input_data}")
            print(f"Error:\n{error}")
        elif output.strip() != expected_output:
            print(f"❌ Test failed for input:\n{input_data}")
            print(f"Expected:\n{expected_output}")
            print(f"Got:\n{output}")
        else:
            print(f"✅ Test passed for input:\n{input_data.strip()}")

if __name__ == "__main__":
    test_echo()
