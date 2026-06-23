# Hands-on #3: Modellazione UML del Running Project

Questo modulo contiene i diagrammi UML realizzati per progettare l'architettura software del sistema a partire dai requisiti e dalle storie d'utente precedentemente definiti. I diagrammi sono stati sviluppati utilizzando il linguaggio di modellazione a oggetti standard (UML) per catturare sia gli aspetti statici che quelli dinamici della piattaforma.

---

## Indice dei Contenuti
1. [Descrizione dei Diagrammi](#descrizione-dei-diagrammi)
2. [Vista Statica](#1-class-diagram-diagramma-delle-classi)
3. [Vista Dinamica e Comportamentale](#2-activity-diagram-diagramma-delle-attivita)
   - [Diagramma delle Attività](#2-activity-diagram-diagramma-delle-attivita)
   - [Diagramma di Sequenza](#3-sequence-diagram-diagramma-di-sequenza)
   - [Diagramma degli Stati](#4-state-diagram-diagramma-degli-stati)
4. [Strumenti Utilizzati](#strumenti-utilizzati)
5. [Come Visualizzare i Diagrammi](#come-visualizzare-i-diagrammi)

---

## Descrizione dei Diagrammi

La progettazione si articola su quattro viste complementari, essenziali per una comprensione olistica dell'architettura prima della fase di codifica:

### 1. Class Diagram (Diagramma delle Classi)
* **Scopo:** Modella la struttura statica dell'applicazione.
* **Dettagli:** Identifica le entità principali del dominio, i loro attributi (visibilità privata/pubblica), i metodi principali e le relazioni strutturali come associazione, aggregazione, composizione ed ereditarietà. Definisce inoltre la molteplicità delle relazioni.

### 2. Activity Diagram (Diagramma delle Attività)
* **Scopo:** Rappresenta la logica di flusso e il comportamento dinamico del sistema durante l'esecuzione di un processo principale.
* **Dettagli:** Evidenzia i flussi di controllo, i bivi decisionali (decision nodes), i punti di sincronizzazione (fork e join per attività parallele) e gli stati iniziali/finali dei macro-processi utente.

### 3. Sequence Diagram (Diagramma di Sequenza)
* **Scopo:** Illustra l'interazione temporale tra gli oggetti del sistema e gli attori esterni.
* **Dettagli:** Specifica lo scambio dei messaggi (sincroni e asincroni), il ciclo di vita e i periodi di attivazione degli oggetti, e l'ordine cronologico delle chiamate necessarie per soddisfare uno scenario d'uso specifico (es. casi d'uso critici o storie d'utente principali).

### 4. State Diagram (Diagramma degli Stati)
* **Scopo:** Descrive il ciclo di vita di un'entità critica del sistema.
* **Dettagli:** Traccia i vari stati discreti in cui l'entità può trovarsi, gli eventi scatenanti, le condizioni di guardia e le azioni associate alle transizioni che ne determinano il cambiamento di stato.

---

## Strumenti Utilizzati
* **Modellazione:** [Inserisci qui lo strumento, es: Lucidchart / StarUML / Draw.io / Mermaid]
* **Documentazione:** Markdown per la stesura dell'indice e della guida strutturata.

---

## Come Visualizzare i Diagrammi

I diagrammi sono integrati direttamente all'interno della repository. Puoi visualizzarli in tre modi diversi:
1. **Rendering automatico:** Se i diagrammi sono scritti in codice (es. Mermaid), GitHub/GitLab eseguirà il rendering automatico all'interno dei file markdown.
2. **File Asset:** Le esportazioni ad alta risoluzione in formato grafico (.png / .svg) sono disponibili all'interno della cartella di progetto /assets o /diagrams.
3. **Estensioni IDE:** Utilizzando VS Code o IDE compatibili, consigliamo l'uso di estensioni dedicate alla preview dei file grafici o del codice di modellazione associato.

---
*Progetto sviluppato nell'ambito del modulo Running Project. Tutti i diritti riservati.*
