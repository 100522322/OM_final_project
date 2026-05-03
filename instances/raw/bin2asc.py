import sys
import os

def bin_to_asc(input_file):
    if not input_file.endswith('.b'):
        print("Error: El archivo debe terminar en .b")
        return

    output_file = input_file[:-2]  # Quita el .b

    try:
        with open(input_file, 'rb') as f:
            # 1. Leer el tamaño del preámbulo (texto inicial)
            line = f.readline().decode('ascii').strip()
            preamble_len = int(line)

            # 2. Leer el preámbulo
            preamble = f.read(preamble_len).decode('ascii')

            # 3. Extraer N (vértices) del preámbulo
            num_vertices = 0
            for p_line in preamble.split('\n'):
                if p_line.startswith('p edge'):
                    parts = p_line.split()
                    num_vertices = int(parts[2])
                    break

            if num_vertices == 0:
                print("Error: No se encontró la definición 'p edge' en el preámbulo.")
                return

            # 4. Leer la matriz binaria y escribir el archivo .col
            with open(output_file, 'w') as out:
                out.write(preamble)

                # Mascaras para leer bits (equivalente a masks[8] en C)
                masks = [0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80]

                for i in range(num_vertices):
                    # Cada fila i en el formato binario lee (i+8)//8 bytes
                    num_bytes = (i + 8) // 8
                    row_data = f.read(num_bytes)

                    for j in range(i + 1):
                        byte_idx = j >> 3
                        bit_idx = 7 - (j & 0x07)

                        if row_data[byte_idx] & masks[bit_idx]:
                            # Escribir arista (DIMACS usa base 1, por eso +1)
                            out.write(f"e {i+1} {j+1}\n")

        print(f"Éxito: Archivo convertido en '{output_file}'")

    except Exception as e:
        print(f"Error durante la conversión: {e}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Uso: python translator.py nombre_archivo.b")
    else:
        bin_to_asc(sys.argv[1])