# Aplicación OCR - Android

### `onCreate(Bundle savedInstanceState)`
- **Descripción:** Método llamado cuando se crea la actividad.
- **Parámetros:**
  - `savedInstanceState` (Bundle): Estado previamente guardado de la actividad.

### `recognizeTextFromImage()`
- **Descripción:** Reconoce el texto en la imagen seleccionada.

### `showInputImageDialog()`
- **Descripción:** Muestra un menú emergente para seleccionar la fuente de la imagen (cámara o galería).

### `pickImageGallery()`
- **Descripción:** Abre la galería para seleccionar una imagen.

### `pickImageCamera()`
- **Descripción:** Abre la cámara para capturar una imagen.

### `checkStoragePermission()`
- **Descripción:** Verifica si se han otorgado permisos de almacenamiento.
- **Retorno:** Booleano (true si se otorgaron los permisos, false si no).

### `requestStoragePermission()`
- **Descripción:** Solicita permisos de almacenamiento.

### `checkCameraPermissions()`
- **Descripción:** Verifica si se han otorgado permisos de cámara y almacenamiento.
- **Retorno:** Booleano (true si se otorgaron los permisos, false si no).

### `requestCameraPermissions()`
- **Descripción:** Solicita permisos de cámara y almacenamiento.

### `onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults)`
- **Descripción:** Maneja los resultados de la solicitud de permisos.
- **Parámetros:**
  - `requestCode` (int): Código de la solicitud.
  - `permissions` (String[]): Arreglo de permisos solicitados.
  - `grantResults` (int[]): Arreglo de resultados de la solicitud de permisos.

### `galleryActivityResultLauncher`
- **Descripción:** Maneja el resultado de la selección de imagen desde la galería.
- **Parámetros:**
  - `result` (ActivityResult): Resultado de la actividad.

### `cameraActicityResultLauncher`
- **Descripción:** Maneja el resultado de la captura de imagen desde la cámara.
- **Parámetros:**
  - `result` (ActivityResult): Resultado de la actividad.

### `OnSuccessListener<Text>`
- **Descripción:** Maneja el éxito del reconocimiento de texto.
- **Parámetros:**
  - `text` (Text): Texto reconocido.

### `OnFailureListener`
- **Descripción:** Maneja el fracaso del reconocimiento de texto.
- **Parámetros:**
  - `e` (Exception): Excepción que indica el motivo del fracaso.


