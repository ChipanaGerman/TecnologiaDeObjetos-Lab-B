"""Genera PDF y video a partir del informe y capturas Qt reales existentes."""
from pathlib import Path
from html import escape
import cv2
import numpy as np
from PIL import Image, ImageDraw, ImageFont
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, Image as PdfImage, PageBreak, KeepTogether
from reportlab.lib.styles import getSampleStyleSheet
from reportlab.lib import colors
from reportlab.lib.enums import TA_LEFT
from reportlab.lib.pagesizes import A4

root = Path(__file__).resolve().parents[1]
evidence = root/'evidencias'
styles = getSampleStyleSheet()
styles['Normal'].fontName = 'Helvetica'
styles['Normal'].fontSize = 10
styles['Normal'].leading = 14
styles['Normal'].spaceAfter = 8
for name in ['Title', 'Heading1', 'Heading2']:
    styles[name].textColor = colors.HexColor('#173457')
story = []
for paragraph in (root/'INFORME.md').read_text(encoding='utf-8').split('\n\n'):
    paragraph = paragraph.strip()
    if not paragraph:
        continue
    if paragraph.startswith('# '):
        story.append(Paragraph(escape(paragraph[2:]), styles['Title']))
        story.append(Spacer(1, 12))
    elif paragraph.startswith('## '):
        story.append(Paragraph(escape(paragraph[3:]), styles['Heading2']))
    else:
        story.append(Paragraph(escape(paragraph).replace('\n', '<br/>'), styles['Normal']))

for image, title, caption in [
    ('02_crear.png', 'Evidencia: creación de actividad', 'El botón de la vista emite la solicitud; el controlador utiliza Factory Method.'),
    ('03_importar.png', 'Evidencia: integración del CSV', 'El adaptador importa los tres tipos desde el formato heredado.'),
    ('04_errores.png', 'Evidencia: errores por línea', 'Una fila aceptada y cuatro rechazadas. Los motivos se muestran al usuario.'),
    ('05_duplicados.png', 'Evidencia: reimportación', 'Las actividades existentes no se duplican al volver a cargar el archivo.')]:
    story += [PageBreak(), Paragraph(title, styles['Heading1']), Paragraph(caption, styles['Normal'])]
    with Image.open(evidence/image) as im:
        w, h = im.size
    story.append(PdfImage(str(evidence/image), width=490, height=490*h/w))

for name in ['clases', 'crear', 'listar', 'cargar']:
    path = root/'diagramas'/f'{name}.png'
    if path.exists():
        story += [PageBreak(), Paragraph('Diagrama: '+name, styles['Heading1'])]
        with Image.open(path) as im:
            w,h = im.size
        ratio = min(490/w, 670/h)
        story.append(PdfImage(str(path), width=w*ratio, height=h*ratio))

def footer(canvas, doc):
    canvas.setFont('Helvetica', 8)
    canvas.setFillColor(colors.HexColor('#62758a'))
    canvas.drawString(45, 24, 'UNSA | Tecnologia de Objetos | Laboratorio 09 | Chipana - Baca')
    canvas.drawRightString(A4[0]-45, 24, str(doc.page))

SimpleDocTemplate(str(root/'INFORME_LAB09_Chipana_Baca.pdf'), pagesize=A4, rightMargin=45, leftMargin=45, topMargin=40, bottomMargin=40).build(story, onFirstPage=footer, onLaterPages=footer)

font_path = 'C:/Windows/Fonts/segoeui.ttf'
font = ImageFont.truetype(font_path, 25)
small = ImageFont.truetype(font_path, 20)
steps = [
    ('01_inicio.png', '1. Agenda académica con Qt 6', 'MVC: la vista recoge datos; el controlador coordina; el modelo valida.'),
    ('02_crear.png', '2. Crear con Factory Method', 'Tarea, Examen y Proyecto comparten una política de validación.'),
    ('03_importar.png', '3. Importar con Adapter', 'El CSV heredado aporta tres actividades mediante IRepositorio.'),
    ('04_errores.png', '4. Validar cada fila', 'Resultado: 1 aceptada y 4 rechazadas, con línea y motivo.'),
    ('05_duplicados.png', '5. Conservar el estado', 'Reimportar rechaza duplicados. Qt Test: 13 casos aprobados.')]
video = cv2.VideoWriter(str(evidence/'demostracion.mp4'), cv2.VideoWriter_fourcc(*'mp4v'), 10, (1280, 900))
if not video.isOpened():
    raise RuntimeError('No se pudo abrir el codificador MP4')
for filename, title, subtitle in steps:
    frame = Image.new('RGB', (1280,900), '#e6edf5')
    draw = ImageDraw.Draw(frame)
    draw.text((30,14), title, font=font, fill='#173457')
    draw.text((30,54), subtitle, font=small, fill='#264763')
    screenshot = Image.open(evidence/filename).convert('RGB')
    screenshot.thumbnail((1200,760))
    frame.paste(screenshot, ((1280-screenshot.width)//2, 100))
    draw.text((30,865), 'Chipana - Baca | Capturas Qt reales por etapas | Sin audio', font=small, fill='#264763')
    bgr = cv2.cvtColor(np.asarray(frame), cv2.COLOR_RGB2BGR)
    for _ in range(80): video.write(bgr)
video.release()
capture = cv2.VideoCapture(str(evidence/'demostracion.mp4'))
assert capture.isOpened() and int(capture.get(cv2.CAP_PROP_FRAME_COUNT)) == 400
capture.release()
print('PDF generado. Video verificado: 400 cuadros, 40 segundos, 1280x900.')
